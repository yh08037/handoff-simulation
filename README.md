# handoff-simulation


![histogram](./images/hist.png)

![result](./images/result.png)


## Test environment
- Ubuntu 18.04
- gcc 7.5.0
- Python 3.6.9


## Execution
```
make
./simulator
python3 visualize.py
```
### Remove generated files
```
make clean
```

## Test execution
```
make test
./test <options>
python3 histogram.py
```

### Option parameters
```
-n : number of iteration
  10000 - default
-r : average size of cell [meter]
  500 - default
-s : average speed of node [kilometer/hour]
  4 - default
-d : average distance of node [meter]
  100 - default
-t : average call duration [minute]
  2 - default
-v : verbose 
  0 - only prints result of execution (default)
  1 - prints all details of execution
```


### Remove generated files
```
make clean_test
```