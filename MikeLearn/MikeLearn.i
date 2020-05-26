%module MikeLearn
%{
#include "MikeLearn.h"
%}

%include "std_vector.i"
namespace std {
    %template(FloatVector)    vector<float>;
}

%include "MikeLearn.h"