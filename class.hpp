#ifndef CLASS_HPP 
#define CLASS_HPP_ 1

#include <iostream>
#include <vector>
#include <map>

class Class_declaration {
    
public:
    virtual std::string get_encapsulation()=0;
    virtual std::string get_type()=0;
    virtual char get_name()=0;
    virtual bool typecheck() = 0;
};

class Class {
    
public:
    Class()
    {}
    
    Class(char name,std::vector<Class_declaration*> cd)
    :_name(name),_cd(cd)
    {}
    
    bool typecheck();
    std::string get_type(char d);
    std::vector<Class_declaration*> get_declarations() {
     
        return _cd;
    }
    char get_name() {
     
        return _name;
    }
    
private:
    char _name;
    std::vector<Class_declaration*> _cd;
};



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
    
    std::string get_encapsulation();
    bool typecheck();
    
private:
    
    std::string _encapsulation;
    std::string _type;
    char _name;
};

class Statement {
  
public:
    virtual bool typecheck() = 0;
    
};

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
    
    std::string get_encapsulation();
    bool typecheck();
    
private:
    std::string _encapsulation;
    std::string _type;
    char _name;
    std::vector<Statement*> _body;
};

class Expression {

public:
    virtual std::string typecheck() = 0;
    
};

class Expression_statement : public Statement {
    
public:
    Expression_statement(Expression *e) : _e(e)
    {}
    
    bool typecheck();
private:
    Expression *_e;
};

class Assignment : public Statement {

public:
    Assignment(Expression *rhs, char name) : _rhs(rhs), _name(name)
    {}
    
    bool typecheck();
private:
    Expression *_rhs;
    char _name;
};

class Declaration : public Statement {
    
public:
    Declaration (char name, std::string type)
        : _name(name), _type(type)
    {}
    
    bool typecheck();
private:    
    char _name;
    std::string _type;
};

class Declaration_and_assigment : public Statement {

public:
    Declaration_and_assigment(std::string type,Expression *rhs, char name)
        : _type(type), _rhs(rhs), _name(name)
    {}
    
    bool typecheck();
private:
    std::string _type;
    Expression *_rhs;
    char _name;
};

class Variable : public Expression {
    
public:
    Variable()
    {}
    
    Variable(char name, std::string type) 
    : _name(name), _type(type)
    {}
    
    std::string typecheck();
    std::string get_type() {
            
        return _type;
    }
private:
    char _name;
    std::string _type;
};

class Constant : public Expression {

    
public:
    Constant(std::string type) 
    : _type(type)
    {}
    
    std::string typecheck();
    std::string get_type() {
        
        return _type;
    }
private:
    std::string _type;
    
};

class Addition : public Expression {
    
public:
    Addition(Expression *lhs, Expression *rhs)
    : _lhs(lhs), _rhs(rhs)
    {}
    
    std::string typecheck();
private:
    Expression *_lhs, *_rhs;
};

class Method_call : public Expression {
    
public:
    Method_call(char varname, char name) 
    : _varname(varname), _name(name)
    {}
    
    std::string typecheck();
private:
    char _varname;
    char _name;
};

class Attribute_call : public Expression {
    
public:
    Attribute_call(char varname, char name) 
    : _varname(varname), _name(name)
    {}
    
    std::string typecheck();
private:
    char _varname;
    char _name;
};

class Function_call : public Expression {
    
public:
    Function_call(char name) 
    :  _name(name)
    {}
    
    std::string typecheck();
private:
    char _name;
};


#endif