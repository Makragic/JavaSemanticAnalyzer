#include "class.hpp"
#include <iostream>
#include <vector>
#include <map>

extern std::map<char,Class> _class_table;
extern std::map<char,Variable> _local_table;

bool Class::typecheck() {
    
    for(auto d : _cd)
        if(!d->typecheck())
            return false;
    
    return true;
}

std::string Class::get_type(char d) {
    
    for(auto i : _cd)
        if(i->get_name() == d)
            return i->get_type();

    return "false";
    
}

bool Variable_declaration::typecheck(){
    
    return true;
}

bool Function_declaration::typecheck(){
    
    int type_error = 0;
    for(Statement *i : _body)
        if(!i->typecheck())
            type_error = 1;
        
    if(!type_error)    
        return true;
    else
        return false;
}

bool Expression_statement::typecheck() {
    
    if(_e->typecheck() == "false") {
        
        std::cout << _e->print() << std::endl;
        for(auto string : _e->get_errors())
            std::cout << "> " << string << std::endl;
        return false;
    }
    else
        return true;
}

bool Assignment::typecheck(){
    
    
    if(!_local_table.count(_name)) {
        
        std::cout << "Greska pri pokusaju dodele: " << std::endl;
        std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
        std::cout << "> Ne postoji lokalna promenljiva " << std::string(1,_name) << "." << std::endl;
        return false;
    }
    
    std::string rhs_typecheck = _rhs->typecheck();
    if((_local_table[_name].get_type() == "double" &&  rhs_typecheck=="int") || 
        (_local_table[_name].get_type() == "int" &&  rhs_typecheck=="double"))
        return true;
    
    if(_local_table[_name].get_type() == rhs_typecheck)
        return true;
    else {
        
        std::cout << "Greska pri pokusaju dodele: " << std::endl;
        std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
        for(auto string : _rhs->get_errors())
            std::cout << "> " << string << std::endl;
        return false;
    }
}

bool Declaration::typecheck(){
    
    return true;
}

bool Declaration_and_assigment::typecheck(){
    
    std::string rhs_typecheck = _rhs->typecheck();
    
    if(_type ==rhs_typecheck)
        return true;
    
    if ((_type == "double" && rhs_typecheck == "int") || (_type == "int" && rhs_typecheck == "double"))
        return true;
    
    std::cout << "Greska pri pokusaju deklaracije i dodele: " << std::endl;
    std::cout <<  _type << " " << _name << " = " << _rhs->print() << ";" << std::endl;
    std::cout << "> Nekompatibilni tipovi." << std::endl;
    for(auto string : _rhs->get_errors())
            std::cout << "> " << string << std::endl;
    
    return false;
}

std::string Variable::typecheck(){
    
    return _type;
    
}

std::string Constant::typecheck(){
    
    return _type;
}

std::string Addition::typecheck(){
    
    std::string lhs_type = _lhs->typecheck();
    std::string rhs_type = _rhs->typecheck();
    
    if(lhs_type==rhs_type)
        return lhs_type;
    
    if((lhs_type=="double" && rhs_type=="int") || (lhs_type=="int" && rhs_type=="double"))
        return "double";
    else{
        _errors.push_back("Nekompatibilni tipovi");
        for(auto string : _lhs->get_errors())
            _errors.push_back(string);
        for(auto string : _rhs->get_errors())
            _errors.push_back(string);
        return "false";
    }
}

std::string Variable_declaration::get_encapsulation(){
    
    return _encapsulation;
}

std::string Function_declaration::get_encapsulation(){
    
    return _encapsulation;
}

std::string Method_call::typecheck(){
    
    if(!_local_table.count(_varname)){
        
        _errors.push_back("Promenljiva " + std::string(1,_varname) + " nije lokalna promenljiva.");
        return "false";
    }
    
    if(!_class_table.count(_local_table[_varname].get_type()[0])){
        
        _errors.push_back("Ne postoji klasa " + std::string(1,_local_table[_varname].get_type()[0]) + ".");
        return "false";
    }
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
        
        _errors.push_back("Metod " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
        return "false";
    }
    
    bool exists = false;
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name) 
            exists = true;
    
    if(!exists){
        
        _errors.push_back("Metod " + print() + " ne postoji.");
        return "false";
        
    }
    
    return _class_table[_local_table[_varname].get_type()[0]].get_type(_name);
}

std::string Attribute_call::typecheck(){
    
    if(!_local_table.count(_varname)){
        
        _errors.push_back("Promenljiva " + std::string(1,_varname) + " nije lokalna promenljiva.");
        return "false";
    }
    if(!_class_table.count(_local_table[_varname].get_type()[0])){
        
        _errors.push_back("Ne postoji klasa " + std::string(1,_local_table[_varname].get_type()[0]) + ".");
        return "false";
    }
    
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
        
        _errors.push_back("Atribut " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
        return "false";
    }
    
    bool exists = false;
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name) 
            exists = true;
    
    if(!exists){
        
        _errors.push_back("Atribut " + print() + " ne postoji.");
        return "false";
        
    }
    
    
    return _class_table[_local_table[_varname].get_type()[0]].get_type(_name);
}

std::string Function_call::typecheck(){
    
    if(!_local_table.count(_name)){
        
        _errors.push_back("Promenljiva " + std::string(1,_name) + " nije lokalna promenljiva.");
        return "false";
    }
    else
        return _local_table[_name].typecheck();
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




