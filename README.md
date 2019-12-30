# ball-intersection-detection

A simple python library to find out all intersection of given k-D balls efficiently.

## Installing
```
git clone https://github.com/cthbst/ball-intersection-detection.git
cd ball-intersection-detection
bash setup.sh
```

## How to use it?
Example 
- ball 0: center (1,2,3) radius 5
- ball 1: center (7,3,5) radius 8
- ball 2: center (-1,-4,7.5) radius 6

Format
- Concate center and radius to a python list. For example (1,2,3) and 5 became [1,2,3,5].
```
from checkCollisions import checkCollisions

result = checkCollisions(
        [ 
            [1,2,3,5],
            [7,3,5,8],
            [-1,-4,7.5,6],
        ]
)
```

## Demo
```
cd examples
./Demo
```

## Test
```
make test
```
