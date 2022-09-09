# ThreadingBenchmark
Benchmark on simple cases ( like overhead on std::async and std::thread , etc)

## specifications
- threads/future: 50
- cpu: corei9-12900k (boosted on middle level)

#### result

```
CPU Caches:
  L1 Data 48 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1280 KiB (x12)
  L3 Unified 30720 KiB (x1)
Load Average: 1.53, 1.03, 0.98
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
***WARNING*** Library was built as DEBUG. Timings may be affected.
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
threadIt            592271 ns       582381 ns         1137
asyncItDefault      620760 ns       615102 ns         1129
asyncItDeffered    2698176 ns      2698139 ns          259
asyncItAsync        614557 ns       608337 ns         1134
```


### Requirements:
to build and run application:
- C++ compiler (std >= c++14)
- google benchmark v1.7.0
