#ifndef ASSERTIONS_HPP
#define ASSERTIONS_HPP

//Assertions
//comment line below to disable assertions
#define DEBUG

#ifdef DEBUG
#define rtAssert(condition, message) if(!(condition)){ std::cerr<<(message)<<std::endl; std::abort();}
#else
#define rtAssert(condition, message) ((void)0)
#endif


#endif // ASSERTIONS_HPP
