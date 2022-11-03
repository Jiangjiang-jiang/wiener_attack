# wiener_attack
A variant C implement of Qin’s algorithm applied to Wiener’s Attack for RSA. The attack details are shown in [analysis.pdf](https://github.com/Jiangjiang-jiang/wiener_attack/blob/main/analysis.pdf).
# Usage
The binary file `wiener_attack` can be run successfully in Ubuntu16.04. And more `e,n` values can be tested by changing `wiener_attack.c`. Though the GMP library is used in the code, run a command for compiling: 
```
./build.sh
```

Only make sure [docker](https://www.docker.com/) has been installed.
# Reference
[1] Xu G. On solving a generalized Chinese remainder theorem in the presence of remainder errors[C]//Conference on Geometry, Algebra, Number Theory, and their Information Technology Applications. Springer, Cham, 2016: 461-476.
