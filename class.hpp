#ifndef CLASS_HPP 
#define CLASS_HPP_ 1

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/* Class hierarchy */
class Class; 
class Class_declaration; /* Class contains class declarations which can be: */
class Variable_declaration;
class Function_declaration; 
class Statement; /* Function declaration contains statements which can be: */
class Expression_statement;
class Assignment;
class Declaration;
class Declaration_and_assigment;
class Expression; /* Expression can be: */
class Variable;
class Constant;
class Addition;
class Method_call;
class Attribute_call;
class Function_call;

/*                                CLASS                                    */
class Class {
    
public:
    Class()
    {}
    
    Class(char name, std::vector<Class_declaration*> cd, std::map<char, Variable> class_local, std::map<char, std::map<char, Variable> > function_local) 
    :_name(name),_cd(cd), _class_local(class_local){
        
        _function_local.insert(function_local.begin(), function_local.end());
    }

    std::vector<Class_declaration*> get_declarations() {
     
        return _cd;
    }

    char get_name() {
     
        return _name;
    }
    
    bool typecheck();
    std::string get_type(char d);
  
private:
    char _name;
    std::vector<Class_declaration*> _cd;
    std::map<char,Variable> _class_local;
    std::map<char, std::map<char, Variable> > _function_local;
};

/*                                CLASS DECLARATION                             */
class Class_declaration {
    
public:
    virtual std::string get_encapsulation()=0;
    virtual std::string get_type()=0;
    virtual char get_name()=0;
    virtual bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local) = 0;
};

/*                              VARIABLE DECLARATION                             */
class Variable_declaration : public Class_declaration {
  
public:
    Variable_declaration(std::string encapsulation, std::string type, char name)
    : _encapsulation(encapsulation), _type(type), _name(name)
    {}
    
    std::string get_type() {
     
        return _type;
    }
    
    char get_name(){
     
        return _name;
    }
    
    std::string get_encapsulation() {
        
        return _encapsulation;
    }
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local);
    
private:
    
    std::string _encapsulation;
    std::string _type;
    char _name;
};

/*                                FUNCTION DECLARATION                           */
class Function_declaration : public Class_declaration {

public:
    Function_declaration(std::string encapsulation, std::string type, char name, std::vector<Statement*> body) 
    : _encapsulation(encapsulation), _type(type), _name(name), _body(body)
    {}
    
    std::string get_type() {
     
        return _type;
    }
    
        char get_name(){
     
        return _name;
    }
    
    std::string get_encapsulation() {
     
        return _encapsulation;
    }
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local);
    
private:
    std::string _encapsulation;
    std::string _type;
    char _name;
    std::vector<Statement*> _body;
};

/*                                STATEMENT                                    */

class Statement {
  
public:
    virtual bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name) = 0;
    
};

class Expression_statement : public Statement {
    
public:
    Expression_statement(Expression *e) : _e(e)
    {}
    
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
private:
    Expression *_e;
};

/*                                ASSIGNMENT                                    */
class Assignment : public Statement {

public:
    Assignment(Expression *rhs, char name) : _rhs(rhs), _name(name)
    {}
    
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);

private:
    Expression *_rhs;
    char _name;
};

/*                             DECLARATION                                    */
class Declaration : public Statement {
    
public:
    Declaration (char name, std::string type)
        : _name(name), _type(type)
    {}
    
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);

private:    
    char _name;
    std::string _type;
};

/*                   DECLARATION AND ASSIGNMENT                                 */
class Declaration_and_assigment : public Statement {

public:
    Declaration_and_assigment(std::string type,Expression *rhs, char name)
        : _type(type), _rhs(rhs), _name(name)
    {}
    
    bool typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);

private:
    std::string _type;
    Expression *_rhs;
    char _name;
};

/*                                EXPRESSION                                    */
class Expression {

public:
    virtual std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name) = 0;
    virtual std::string print() = 0;
    virtual std::vector<std::string> get_errors() = 0;
    
};

/*                                VARIABLE                                    */
class Variable : public Expression {
    
public:
    Variable()
    {}
    
    Variable(char name, std::string type) 
    : _name(name), _type(type)
    {}
    
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::string print();

    std::string get_type() {
            
        return _type;
    }

    std::vector<std::string> get_errors() {
     
        return _errors;
    }
private:
    char _name;
    std::string _type;
    std::vector<std::string> _errors;
};

/*                                CONSTANT                                    */
class Constant : public Expression {

    
public:
    Constant(std::string type, std::string value)  
    : _type(type), _value(value)
    {}
    
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::string print();
    std::string get_type() {
        
        return _type;
    }
    std::vector<std::string> get_errors() {
     
        return _errors;
    }

private:
    std::string _type;
    std::string _value;
    std::vector<std::string> _errors;
};

/*                                ADDITION                                    */
class Addition : public Expression {
    
public:
    Addition(Expression *lhs, Expression *rhs)
    : _lhs(lhs), _rhs(rhs)
    {}
    
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::string print();
    std::vector<std::string> get_errors() {
     
        return _errors;
    }

private:
    Expression *_lhs, *_rhs;
    std::vector<std::string> _errors;
};

/*                                METHOD CALL                                  */
class Method_call : public Expression {
    
public:
    Method_call(char varname, char name) 
    : _varname(varname), _name(name)
    {}
    
    std::string print();
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::vector<std::string> get_errors() {
     
        return _errors;
    }
private:
    char _varname;
    char _name;
    std::vector<std::string> _errors;
};

/*                                ATTRIBUTE CALL                                 */
class Attribute_call : public Expression {
    
public:
    Attribute_call(char varname, char name) 
    : _varname(varname), _name(name)
    {}
    
    std::string print();
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::vector<std::string> get_errors() {
     
        return _errors;
    }
private:
    char _varname;
    char _name;
    std::vector<std::string> _errors;
};

class Function_call : public Expression {
    
public:
    Function_call(char name) 
    :  _name(name)
    {}
    
    std::string print();
    std::string typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name);
    std::vector<std::string> get_errors() {
     
        return _errors;
    }
private:
    char _name;
    std::vector<std::string> _errors;
};

#endif
