#include "class.hpp"
#include <iostream>
#include <vector>
#include <map>

extern std::map<char,Class> _class_table;

/* If each class declaration is correct then whole class is correct */
bool Class::typecheck() {
    
    for(auto d : _cd)
        if(!d->typecheck(_class_local,  _function_local))
            return false;
    
    return true;
}

/* Returns type of variable or function if it is declared in 
   class, otherwise false 
*/
std::string Class::get_type(char d) {
    
    for(auto i : _cd)
        if(i->get_name() == d)
            return i->get_type();

    return "false";
}

/* Variable declaration is always semantically correct */
bool Variable_declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local){
    
    return true;
}

/* Function declaration is correct if each statement in function is correct */
bool Function_declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local){
    
    bool has_error = false;
    for(Statement *i : _body)
        if(!i->typecheck(class_local, function_local, _name))
            has_error = true;
        
    if(has_error)
	return false;
    else
	return true;
}

/* Checks expression for errors, prints them, returns whether expression is correct or not */
bool Expression_statement::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name) {
    
    if(_e->typecheck(class_local,function_local,name) == "false") {
        
        std::cout << _e->print() << std::endl;
        for(auto string : _e->get_errors())
            std::cout << "> " << string << std::endl;
        return false;
    }
    else
        return true;
}

/* Checks in which map to look for the variable and if right hand side and left hand side are of compatible types */
bool Assignment::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    
    if(!function_local[name].count(_name) && !class_local.count(_name)) {
        
        std::cout << "Assignment error: " << std::endl;
        std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
        std::cout << "> No such variable " << std::string(1,_name) << "." << std::endl;
        return false;
    }
    
    
    std::string rhs_typecheck = _rhs->typecheck(class_local,function_local,name);
    if(function_local[name].count(_name)){
        if((function_local[name][_name].get_type() == "double" &&  rhs_typecheck=="int") || 
            (function_local[name][_name].get_type() == "int" &&  rhs_typecheck=="double"))
            return true;
        if(function_local[name][_name].get_type() == rhs_typecheck)
            return true;
        else {
        
            std::cout << "Assignment error: " << std::endl;
            std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
            for(auto string : _rhs->get_errors())
                std::cout << "> " << string << std::endl;
            return false;
            
        }
    }
    else {
        
        if((class_local[_name].get_type() == "double" &&  rhs_typecheck=="int") || 
            (class_local[_name].get_type() == "int" &&  rhs_typecheck=="double"))
            return true;
        if(class_local[_name].get_type() == rhs_typecheck)
            return true;
        else {
        
            std::cout << "Assignment error: " << std::endl;
            std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
            for(auto string : _rhs->get_errors())
                std::cout << "> " << string << std::endl;
            return false;
        
        }
        
    }
}

/* Declaration is always semantically carrect */
bool Declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return true;
}

/* Checks in which map to look for the variable and if right hand side and left hand side are of compatible types */
bool Declaration_and_assigment::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    std::string rhs_typecheck = _rhs->typecheck(class_local,function_local,name);
    
    if(_type ==rhs_typecheck)
        return true;
    
    if ((_type == "double" && rhs_typecheck == "int") || (_type == "int" && rhs_typecheck == "double"))
        return true;
    
    std::cout << "Declaration and assignment error: " << std::endl;
    std::cout <<  _type << " " << _name << " = " << _rhs->print() << ";" << std::endl;
    std::cout << "> Noncompatable types." << std::endl;
    for(auto string : _rhs->get_errors())
            std::cout << "> " << string << std::endl;
    
    return false;
}

std::string Variable::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return _type;
    
}

std::string Constant::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return _type;
}

std::string Addition::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    std::string lhs_type = _lhs->typecheck(class_local,function_local,name);
    std::string rhs_type = _rhs->typecheck(class_local,function_local,name);
    
    if(lhs_type==rhs_type)
        return lhs_type;
    
    if((lhs_type=="double" && rhs_type=="int") || (lhs_type=="int" && rhs_type=="double"))
        return "double";
    else{
        _errors.push_back("Noncompatable types.");
        for(auto string : _lhs->get_errors())
            _errors.push_back(string);
        for(auto string : _rhs->get_errors())
            _errors.push_back(string);
        return "false";
    }
}



std::string Method_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    if(!class_local.count(_varname) && !function_local[name].count(_varname)){
        
        _errors.push_back("Method " + std::string(1,_varname) + " not declared.");
        return "false";
    }
    
    if(!_class_table.count(class_local[_varname].get_type()[0])){
        
        _errors.push_back("No such class " + std::string(1,class_local[_varname].get_type()[0]) + ".");
        return "false";
    }
    
    if(class_local.count(_varname)){
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Method " + std::string(1,_varname) + "." + std::string(1,_name) + " is private.");
            return "false";
        }
    } 
    else {
        
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Method " + std::string(1,_varname) + "." + std::string(1,_name) + " is private.");
            return "false";
        }
    }

    if(class_local.count(_varname)){
      
        bool exists = false;
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Method " + print() + " doesn't exist.");
            return "false";
            
        }
        
        return _class_table[class_local[_varname].get_type()[0]].get_type(_name);   
   
    }
    else {
        
        bool exists = false;
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Method " + print() + " doesn't exist.");
            return "false";
            
        }
        
        return _class_table[function_local[name][_varname].get_type()[0]].get_type(_name); 
    }
    
}

std::string Attribute_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
     
    if(!class_local.count(_varname) && !function_local[name].count(_varname)){
        
        _errors.push_back("Variable " + std::string(1,_varname) + " not declared.");
        return "false";
    }
    
    if(!_class_table.count(class_local[_varname].get_type()[0])){
        
        _errors.push_back("No such class " + std::string(1,class_local[_varname].get_type()[0]) + ".");
        return "false";
    }
    
    if(class_local.count(_varname)){
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Attribute " + std::string(1,_varname) + "." + std::string(1,_name) + " is private.");
            return "false";
        }
    } 
    else {
        
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Attribute " + std::string(1,_varname) + "." + std::string(1,_name) + " is private.");
            return "false";
        }
    }

    if(class_local.count(_varname)){
      
        bool exists = false;
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Attribute " + print() + " doesn't exist.");
            return "false";
            
        }
        
        return _class_table[class_local[_varname].get_type()[0]].get_type(_name);   
   
    }
    else {
        
        bool exists = false;
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Attribute " + print() + " doesn't exist.");
            return "false";
            
        }
        
        return _class_table[function_local[name][_varname].get_type()[0]].get_type(_name); 
    }
}

std::string Function_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    if(!class_local.count(_name)){
        
        _errors.push_back("Function " + std::string(1,_name) + " not declared.");
        return "false";
    }
    else
        return class_local[_name].typecheck(class_local,function_local,name);
} 

/* ---------------------------------- PRINT ----------------------------- */

std::string Variable::print(){
    
    return std::string(1,_name);
} 

std::string Constant::print(){
    
    return _value;
} 

std::string Addition::print(){
    
    return " " + _lhs->print() + " + " + _rhs->print();
}

std::string Method_call::print(){
    
    return std::string(1,_varname) + "." + std::string(1,_name) + "()";
}

std::string Attribute_call::print(){
    
    return std::string(1,_varname) + "." + std::string(1,_name);
}

std::string Function_call::print(){
    
    return std::string(1,_name) + "()";
}




