%module MikeLearn
%{
#include "MikeLearn.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "Agent.h"
namespace std {
    %template(FloatVector)   vector<float>;
    %template(FloatVectorVector) vector<vector<float>>;
    %template(IntVector)    vector<int>;
    %template(StringVector) vector<string>;
    %template(AgentVector) vector<Agent*>;
}
%include "MikeLearn.h"
%include "Model.h"
%include "Logger.h"
%include "NeuralNetwork.h"
%include "ClassificationOptimizer.h"
%include "Connect4Environment.h"
%include "ReinforcementClassificationOptimizer.h"


