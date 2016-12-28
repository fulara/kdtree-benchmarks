# kdtree-benchmarks
Benchmarking implementation of  Kdtree implementations. Currently only CGAL and mine  
[mine](https://github.com/fulara/kdtree-rust)  
[CGAL](http://www.cgal.org/)  

The version of the repo is not really to be easily used.. :)  
It requires CGAL/boost to be installed on the system as of the time of writing this the conan does not have CGAL.  
Results of the benchmark:  
```
Benchmark                           Time           CPU Iterations
-----------------------------------------------------------------
Cgal_tree_buildup/10             2226 ns       2221 ns     313336
Cgal_tree_buildup/100           18357 ns      18315 ns      37968
Cgal_tree_buildup/1000         288135 ns     287345 ns       2369
Cgal_tree_buildup/9.76562k    3296740 ns    3290815 ns        211
Cgal_tree_buildup/97.6562k   42909150 ns   42813307 ns         12
Cgal_tree_buildup/976.562k  734566227 ns  733267760 ns          1
Cgal_tree_lookup/10                72 ns         72 ns    9392612
Cgal_tree_lookup/100               95 ns         95 ns    7103628
Cgal_tree_lookup/1000             174 ns        174 ns    4010773
Cgal_tree_lookup/9.76562k         268 ns        267 ns    2759487
Cgal_tree_lookup/97.6562k         881 ns        876 ns    1262454
Cgal_tree_lookup/976.562k         993 ns        991 ns     713751
Rust_tree_buildup/10              726 ns        724 ns     856791
Rust_tree_buildup/100            7103 ns       7092 ns      96132
Rust_tree_buildup/1000          84879 ns      84720 ns       7927
Rust_tree_buildup/9.76562k    1012983 ns    1010856 ns        630
Rust_tree_buildup/97.6562k   12406293 ns   12382399 ns         51
Rust_tree_buildup/976.562k  197175067 ns  196763387 ns          3
Rust_tree_lookup/10                62 ns         62 ns   11541505
Rust_tree_lookup/100              139 ns        139 ns    4058837
Rust_tree_lookup/1000             220 ns        220 ns    2890813
Rust_tree_lookup/9.76562k         307 ns        307 ns    2508133
Rust_tree_lookup/97.6562k         362 ns        362 ns    2035671
Rust_tree_lookup/976.562k         442 ns        441 ns    1636130
```
