class A {

 public:
   A() {};

  A(int x) { setX(x); }

  int getX() { return(x); }   
  void setX(int val) { x = val; }   

 protected:
   int x;

};

class B : public A
{
 public:
     B(int val) : A(val) {};

     int square() {return( getX()* getX());}
};
