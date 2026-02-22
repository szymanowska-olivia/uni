#include <bits/stdc++.h>
using namespace std;

const int IT = 200;

double f(double x){
    return pow(x,5) - x + 1;
}

double df(double x){
    return 5*pow(x,4) - 1;
}

int main(){

    double tol = 1e-14;
    cout << "metoda bisekcji" << endl;
    double l = -2, r = 0, fl = f(l), fr = f(r);
    double res;

    for(int i=1; i<=IT; i++){
        double m = 0.5*(l+r), fm = f(m);
        res = m;
        //cout << "Iteracja: " << i << "  m= " << m << "  f(m)= " << fm << endl; 

        if(fabs(fm) < tol || fabs(r-l) < tol) break;

        if(fl*fm < 0){
            r = m; 
            fr = fm;
        } else {
            l = m; 
            fl = fm;
        }
    }

    cout << res << endl;

    cout << "metoda newtona" << endl;
    double x = -1.5;

    for(int i=1; i<=IT; i++){
        double fx = f(x), dfx = df(x);
        res = x;
        //cout << "Iteracja: " << i << "  x= " << x << "  f(x)= " << fx << "  f'(x)= " << dfx << endl; 

        double dx = fx/dfx;
        x -= dx;

        if(fabs(fx) < tol || fabs(dx) < tol) break;
    }

    cout << res << endl;

    cout << "metoda siecznych" << endl;
    double x0 = -2, x1 = 0;
    double f0 = f(x0), f1 = f(x1);

    for(int i=1; i<=IT; i++){
        if(fabs(f1 - f0) < 1e-30) break;

        double x2 = x1 - f1*(x1 - x0)/(f1 - f0), f2 = f(x2);
        res = x;
        //cout << "Iteracja: " << i << "  x= " << x2 << "  f(x)= " << f2 << endl;

        if(fabs(x2 - x1) < tol || fabs(f2) < tol) break;

        x0 = x1; 
        f0 = f1;
        x1 = x2; 
        f1 = f2;
    }

    cout << res << endl;

    cout << "regula falsi" << endl;
    double a = -2, b = 0;
    double fa = f(a), fb = f(b);

    for(int i=1; i<=IT; i++){
        double xrf = (a*fb - b*fa) / (fb - fa);
        double fx = f(xrf);

        res = x;
        //cout << "Iteracja: " << i << "  x= " << xrf << "  f(x)= " << fx << endl;

        if(fabs(fx) < tol) break;

        if(fa * fx < 0){
            b = xrf; 
            fb = fx;
        } else {
            a = xrf; 
            fa = fx;
        }
    }

    cout << res << endl;

}
