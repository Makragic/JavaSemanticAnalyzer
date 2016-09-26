class A {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
   }
}

class B {
   public A a;
   public string d; 
   public void g() {
     int z = a.x;
     int d; 
     string h = a.y; 
     double m = a.y + d; 
     a.f();
     int y = a.z; 
     int t = a.m; 
     int s = g(); 
   }
}

class C {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.f();
   }
}

class D {
   public A a;
   public string d; 
   public void g() {
     int z = a.x;
     string h = a.y; 
   } 
}

class E {
   public A a;
   public string d; 
   public void g() {
     int z = a.z;
   } 
}

class F {
   public A a;
   public string d; 
   public void g() {
     int t = a.m;
   } 
}

class G {
   public A a;
   public string d; 
   public void g() {
     int t = g();
   } 
}

class H {
   public A a;
   public double d;
   public int q; 
   public void g() {
     double m = a.y + d;
     q = a.y + d;
   } 
}

class I {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.m();
   }
}

class J {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
       p = 4;
   }
}

class K {

  public int x;
  public int q() {

    int x;
    int y;
  }
  public int y;
  public int w() {

    int x;
    int y;
  }
}
