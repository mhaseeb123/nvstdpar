// Cholesky Decomposition: stdpar
#include "argparse/argparse.hpp"
#include "commons.hpp"

#include <execution> // Include the execution header
#include <exec/static_thread_pool.hpp>
#include <experimental/mdspan>
#include <stdexec/execution.hpp>
#include <vector>

using namespace std;
using namespace stdexec;
using stdexec::sync_wait;


template<typename T>
void Cholesky_Decomposition(std::vector<T> & vec, int n)
{
    std::vector<std::vector<T>> lower(n, std::vector<T>(n, 0));

    using view_2d = std::extents<T, std::dynamic_extent, std::dynamic_extent>;
    auto matrix = std::mdspan<T, view_2d, std::layout_right>(vec.data(), n,n);
    

    //  // scheduler from a thread pool
    exec::static_thread_pool pool(n);// number of parallel sec
    stdexec::scheduler auto sch = pool.get_scheduler();
    stdexec::sender auto begin = stdexec::schedule(sch);

    // Decomposing a matrix into Lower Triangular
    for (int i = 0; i < matrix.extent(0); i++) {
        for (int j = 0; j <= i; j++) {
            int sum = 0;
 
            if (j == i) // summation for diagonals
            {   
                auto s = stdexec::just(j, sum)|then(begin)
                        | stdexec::bulk(j, [&](int k, int& sum ){
                           sum += pow(lower[j][k], 2);
                      });  
                 // start summation                     
                auto [summation] = stdexec::sync_wait(std::move(s)).value(); 
                std::cout << "Sum: " << summation << std::endl;
                      
                lower[j][j] = sqrt(matrix(i,j) - summation);
            } else {
                // Evaluating L(i, j) using L(j, j)

                auto s2 =  stdexec::just(j,sum)|then(begin)
                        | stdexec::bulk(j, [&](int i, int j, int k, int& sum ){
                           sum += (lower[i][k] * lower[j][k]);
                      });                  
                auto [summation2] = stdexec::sync_wait(std::move(s2)).value();       

                lower[i][j] = (matrix(i,j) - summation2) / lower[j][j];
            }
        }
    }
 
    // Displaying Lower Triangular and its Transpose
    cout << setw(6) << " Lower Triangular" 
         << setw(30) << "Transpose" << endl;
    for (int i = 0; i < n; i++) {
         
        // Lower Triangular
        for (int j = 0; j < n; j++)
            cout << setw(6) << lower[i][j] << "\t";
        cout << "\t";
         
        // Transpose of Lower Triangular
        for (int j = 0; j < n; j++)
            cout << setw(6) << lower[j][i] << "\t";
        cout << endl;
    }
}
 
// Driver Code for testing
int main()
{
    constexpr int n = 3;
    std::vector<int> v{4, 12, -16,12, 37, -43, -16, -43, 98 };
    Cholesky_Decomposition(v, n);

    return 0;
}


// auto Cholesky_Decomposition_async(int elem){

//      // scheduler from a thread pool
//     exec::static_thread_pool pool(n);// number of parallel sec
//     stdexec::scheduler auto sch = pool.get_scheduler();
//     stdexec::sender auto begin = stdexec::schedule(sch);
    
//     auto s = std::exec::bulk(begin, elem, [&, elem=elem](){
//         std::for_each_n(std::execution::par, counting_iterator(0), j,
//                       [=, j = j, &sum](int32_t k) {
//                     sum += pow(lower[j][elem], 2);
//                       });                  
//     });
//     auto[summation] = stdexec::sync_wait(std::move(s)).value(); 