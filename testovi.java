
/*                                      Specijalni slucajevi                                  */
// SPECIJALNI 1: Netacno (Ne postoji klasa A)
class O {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.f();
   }
}

// SPECIJALNI 2: Netacno (Ponovna deklaracija klase A)
class A {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
   }
}

class A {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
   }
}

/*                                         TESTOVI                                         */
// TEST 1: Tacno
class A {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
   }
}

// TEST 2: Netacno (Ceo primer)
class B {
   public A a;
   public string d; 
   public void g() {
     int z = a.x;
     int d; 
     string h = a.y; 
     double m = y + d; 
     a.f();
     int y = a.z; 
     int t = a.m; 
     int s = g(); 
   }
}

//TEST 3: Tacno
class C {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.f();
   }
}

//TEST 4: Netacno (h je string, a.y je int)
class D {
   public A a;
   public string d; 
   public void g() {
     int z = a.x;
     string h = a.y; 
   } 
}

//TEST 5: Netacno (a.z je private)
class E {
   public A a;
   public string d; 
   public void g() {
     int z = a.z;
   } 
}


//TEST 6: Netacno (a.m ne postoji)
class F {
   public A a;
   public string d; 
   public void g() {
     int t = a.m;
   } 
}

//TEST 7: Netacno (g je void)
class G {
   public A a;
   public string d; 
   public void g() {
     int t = g();
   } 
}

//TEST 8: Tacno (implicitna konverzija)
class H {
   public A a;
   public double d;
   public int q; 
   public void g() {
     double m = a.y + d;
     q = a.y + d;
   } 
}

//TEST 10: Netacno (a.m() ne postoji)
class I {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.m();
   }
}

//TEST 10: Netacno (p promenljiva ne postoji)
class J {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
       p = 4;
   }
}

//k



//Maric:
class Maric {
   public A a;
   public string d; 
   public void g() {
     int z = a.x;
     int d; // OK sakrivamo globalno ime
     string h = a.y; // greska y je int, a h je string
     double m = a.y + d; // OK implicitna konverzija
     a.f();
     int y = a.z; // greska z je private
     int t = a.m; // greska nedefinisano polje
     int s = g(); // greska, g je void
   }
}
map<char,Klasa>
map<char,Promenljiva>

/*                                     Testovi bez komentara                               */

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
     double m = y + d; 
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
   public double d;
   public int q; 
   public void g() {
     double m = a.y + d;
     q = a.y + d;
   } 
}

class J {
   public A a;
   public string d; 
   public void g() {

      int z = a.x;
      a.m();
   }
}

class K {
   public int x, y;
   private int z;
   public double f() {
       x = 0; y = 3;
       z = 2;
       p = 4;
   }
}