//
//  main.cpp
//  Логвіна
//
//  Created by Anhelina Lohvina on 12.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>

//Pi ~ 355/113
#define PI_num 355
#define PI_den 113

//==============EXP======================================
template <int N, int I, int J, int K> class ExpSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return 1 +  float (I)/N /(K + 1) * ExpSeries<N*go, I*go, J*go, (K + 1)*go>::sum();
    }
};
template<int N, int I> class Exp {
public:
    static inline float exponenta() {
        return ExpSeries<N, I, 30, 0>::sum();
    }
};
template<> class ExpSeries<0, 0, 0, 0> {
public:
    static inline float sum() {return 0;}
};

//=============ARSIN======================================
template <int N, int I, int J, int K> class ArsinSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return Exp<N, I>::exponenta() + Exp<N, I>::exponenta() * Exp<N, I>::exponenta() * (2*K+1)
        / (2 * ((K+1) * (2*K + 3))) * ArsinSeries<N*go, I*go, J*go, (K + 1)*go>::sum();
    }
};
template<int N, int I> class Arsin {
public:
    static inline float arsinus() {
        return ArsinSeries<N, I, 30, 0>::sum();
    }
};
template<> class ArsinSeries<0, 0, 0, 0>{
public:
    static inline float sum() {return 0;}
};

//===========ARCOS = pi/2 - ARSIN===========================
template <int N, int I, int J, int K> class ArcosSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return float(PI_num)/PI_den / 2 - Arsin<N, I>::arsinus();
    }
};

template<int N, int I> class Arcos {
public:
    static inline float arcosinus() {
        return ArcosSeries<N, I, 30, 1>::sum();
    }
};

template<> class ArcosSeries<0, 0, 0, 0>{
public:
    static inline float sum() {return 0;}
};

//==============SIN======================================
template <int N, int I, int J, int K> class SinSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return Arcos<N, I>::arcosinus() - Arcos<N, I>::arcosinus() * Arcos<N, I>::arcosinus()
        / ((2*K) * (2*K + 1)) * SinSeries<N*go, I*go, J*go, (K + 1)*go>::sum();
    }
};

template<int N, int I> class Sin {
public:
    static inline float sinus() {
        return SinSeries<N, I, 30, 1>::sum();
    }
};

template<> class SinSeries<0, 0, 0, 0>{
public:
    static inline float sum() {return 0;}
};

//==============COS======================================
template <int N, int I, int J, int K> class CosSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return 1-Sin<N, I>::sinus()*Sin<N, I>::sinus()/((2*K)*(2*K - 1))
        * CosSeries<N*go, I*go, J*go, (K + 1)*go>::sum();
    }
};
template<int N, int I> class Cos {
public:
    static inline float cosinus() {
        return CosSeries<N, I, 30, 1>::sum();
    }
};

template<> class CosSeries<0, 0, 0, 0>{
public:
    static inline float sum() {return 0;}
};

//===============LN=====================================
template <int N, int I, int J, int K> class LogSeries {
public:
    enum { go = (K + 1 != J) };
    static inline float sum() {
        return (Cos<N, I>::cosinus() - 1) / K - (Cos<N, I>::cosinus() - 1)
        * LogSeries<N*go, I*go, J*go, (K + 1)*go>::sum();
    }
};
template<int N, int I> class Log {
public:
    static inline float logariphm() {
        return LogSeries<N, I, 30, 1>::sum();
    }
};
template<> class LogSeries<0, 0, 0, 0>{
public:
    static inline float sum() {return 0;}
};

template<int N, int I> class Calculate {
public:
    static inline float calculate() {
        return Log<N, I>::logariphm();
    }
};
int main(){
    float  answer = Calculate<-2, 1>::calculate();
    double actualAnswer = log(cos(sin(acos(exp(-0.5)))));
    double error = 0;
    error = (actualAnswer - answer) / answer * 100;
    std::cout << "ln(cos(sin(arccos(exp(-0.5))))) = " << std::endl
    << '\t'<<"computed by me "; std::cout.width(15); std::cout << answer << std::endl
    << '\t'<<"computed by computer " << actualAnswer << std::endl;
    std::cout << "the computation error: ";  std::cout.width(10);  std::cout  << abs(error) << " %" << std::endl;
    system("PAUSE");
    return 0;
}
