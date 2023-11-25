#include "geom.h"

Point Point :: operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

Point :: Point(const Point& p){
        x = p.x;
        y = p.y;
    }

double Point::getX() const {
        return x;
    }

double Point::getY() const {
        return y;
    }

Circle::Circle(const Point& c, double r) : center(c), radius(r) {}

Circle::Circle(const Circle& other){
        radius = other.radius;
        center = other.center;
    }

double Circle::getRadius() {
        return radius;
    }

Point Circle::getCenter() {
        return center;
    }

 
	void Circle::findIntersection(const Circle& other, Point& intersection1) const {
        
        double a, b, c, e, d, y, x;
        a = other.center.getX()*other.center.getX() +other.center.getY()*other.center.getY();
		c = (other.center.getX()*other.center.getX() + other.center.getY()*other.center.getY() + radius*radius - other.radius*other.radius)/2;
        b = -2 * other.center.getY()*c;
		e = c*c-radius*radius*other.center.getX()*other.center.getX();
		d = b*b-4*a*e;
		y = ((-1)*b + std::pow(d, 0.5))/(2*a);
		x = (c-y*other.center.getY())/(other.center.getX());

        intersection1 = Point(x, y); 
    }

Circle Circle :: operator =(const Circle& p) {
        radius = p.radius;
        center = p.center;
        return *this;
    }

Point Triangle::getA(){
    return A;
    }

Point Triangle::getB(){
    return B;
}

Point Triangle::getC(){
    return C;
}

void Triangle::print_Triangle(const string& filename) const{
        ofstream file(filename);
		
		double r = 2*BC*std::sin(ang/2);
        if (file.is_open()){
            file << 0 << " " << -10 << " \n";
            file << AB << " " << -10 << " \n\n";
            file << 0 << " " << -11 << " \n";
            file << BC << " " << -11 << " \n\n";
            file << A.getX() << " " << A.getY() << "\n";
            file << B.getX() << " " << B.getY() << "\n";
            file << C.getX() << " " << C.getY() << "\n";
            file << A.getX() << " " << A.getY() << "\n";
            file << "\n";
        
		double eps = 0.01;  
        int numPoints = static_cast<int>(2 * M_PI * AB / eps);
		
        for(int i = 0; i < numPoints; ++i){      
		double angle = i * 2 * M_PI / numPoints;		
		double x = A.getX() + AB * cos(angle);  
		double y = A.getY() + AB * sin(angle);
        file << x << " " << y << "\n";
}
        file << "\n";
            
        numPoints = static_cast<int>(2 * M_PI * BC / eps);
        for(int i = 0; i < numPoints; ++i){
        double angle = i * 2 * M_PI / numPoints;
        double x = A.getX() + BC * cos(angle);
        double y = A.getY() + BC * sin(angle);
        file << x << " " << y << "\n";
}
		file << "\n";
            
            numPoints = static_cast<int>(2 * M_PI * r / eps);
            for(int i = 0; i < numPoints; ++i){
                double angle = i * 2 * M_PI / numPoints;
                double x = BC + r * cos(angle);
                double y =   r * sin(angle);
                file << x << " " << y << "\n";
}
			

         file.close();
        } else { 
            cerr << "Ошибка открытия файла" << filename << "\n"; 
        }

    }

bool Triangle::read_Triangle(const string& namefile){
        ifstream fin(namefile);
        double nAB, nBC, nang;
        if(fin.is_open()){
            if (fin >> nAB >> nBC >> nang){				
				nang = nang*M_PI/180.0;
                if(is_Triangle(nang)){
                    set_Triangle(nAB, nBC, nang);
                    return true;
                } else {
                    cerr << "Не образует треугольник";
                }
                
            } else {
                cerr << "Ошибка чтения\n";
            }
            fin.close();
        } else {
            cerr << "Ошибка открытия файла" << namefile << "\n";
        }
        return false;  
    } 

bool Triangle::is_Triangle(double nang){
        return nang < 180.0;    
    }

void Triangle::set_Triangle(double nAB, double nBC, double nang){
        AB = nAB;
        BC = nBC;
		ang = nang;
		Point F(BC, 0.0);
		double r = 2*BC*std::sin(ang/2);
        A = Point(0.0,0.0);
        B = Point(AB, 0.0);
        Circle c1 = Circle(A, AB); 
        Circle c2 = Circle(A, BC);
        Circle c3 = Circle(F, r);
        Point intersection;
        c2.findIntersection(c3, intersection);
        C = intersection;
    }

    