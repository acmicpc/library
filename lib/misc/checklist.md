RUNTIME ERROR
-------------
* array index out of range
    * not enough size
    * wrong index calculation
* stack overflow
* divided by 0
* operation on invalid iterator
    * set.erase(set.find(x)) when x doesn't exist

WRONG ANSWER
------------
* set or multiset

TIME LIMIT EXCEEDED
-------------------
* memset on large array
* lower_bound(set.begin(), set.end(), x) to set.lower_bound(x)
* save gcd(sin, cos, sqrt, ...) in array
