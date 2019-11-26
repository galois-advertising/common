# util
Common files of galois engine

# build 

```
cd util
mkdir build && cd build
export CC=/usr/local/bin/gcc-8 && export CXX=/usr/local/bin/g++-8; cmake ../; 
make
```

## thread-pool
A thread pool implement used in galois.
[Document](thread-pool/README.md)

## ependingpool
A socket manager by epoll.
 
