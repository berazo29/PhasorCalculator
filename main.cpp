#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;

class Phasor{
private:
    double vector;
    double angle;

    double componentX() const{
        return vector*cos(angle * PI / 180.0);
    }
    double componentY() const{
        return vector*sin(angle * PI / 180.0);
    }

public:
    Phasor(){
        vector=0.0f;
        angle=0.0f;
    }
    Phasor(double v, double a){
        vector = v;
        angle = a;
    }

    double getVector() const{
        return vector;
    }
    double  getAngle() const{
        return angle;
    }
    void setVector(double v){
        vector = v;
    }
    void setAngle(double a){
        angle = a;
    }

    Phasor operator+(Phasor phasor2) const{
        Phasor answer;

        // Same angles can be added without transforming to real numbers
        if (angle == phasor2.getAngle()){
            answer.setVector(vector + phasor2.getVector());
            answer.setAngle(angle);
            return answer;
        }else{
            // Transfor polar to real, add them and set it back to polar
            double a = componentX() +  phasor2.componentX();
            double b = componentY() +  phasor2.componentY();
            double inside = pow(a,2) + pow(b, 2);
            double z = sqrt(inside);
            answer.setVector(z);
            double ang = atan( b/a ) * 180 / PI;
            answer.setAngle(ang);
            return answer;
        }

    }
    Phasor operator*(Phasor phasor2) const{
        Phasor answer;
        answer.setVector(vector * phasor2.getVector());
        answer.setAngle(angle + phasor2.getAngle());
        return answer;
    }
    Phasor operator/(Phasor phasor2) const{
        Phasor ans;
        ans.setVector(vector / phasor2.getVector());
        ans.setAngle(angle - phasor2.getAngle());
        return ans;
    }
};
int main()
{
    Phasor v(220.0,0.0);
    Phasor z1(12.0,45);
    Phasor z2(30,-60);
    Phasor impedance;
    Phasor i;
    impedance = z1 + z2;
    i = v / impedance;

    cout<<"ZTotal = "<< impedance.getVector()<<" "<<impedance.getAngle()<<endl;
    cout<<"I = "<<i.getVector()<<" "<<i.getAngle()<<endl;

    return 0;
}
