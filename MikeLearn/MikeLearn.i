%module MikeLearn
%{
#include "MikeLearn.h"
%}

%include "std_vector.i"
%include "std_string.i"
namespace std {
    %template(FloatVector)   vector<float>;
    %template(FloatVectorVector) vector<vector<float>>;
    %template(IntVector)    vector<int>;
    %template(StringVector) vector<string>;
}

%include "MikeLearn.h"
%include "Model.h"
%include "Logger.h"
%include "NeuralNetwork.h"
%include "ClassificationOptimizer.h"