#include "proxy.hpp"
#include <iostream>
#include "string.h"
#include <memory>

using namespace std;

// ex 1: smart pointer
// ex 2: virtual proxy(this demo)

struct Processor{
    virtual void handle(const string& request) = 0;
    virtual ~Processor() {};
};

struct ComputeEngine : Processor{
    ComputeEngine(const string& env) {
        cout << "ComputeEngine()\n";
        cout << "Initialize Computing Environment: " << env << endl;
    }

    void handle(const string& request) override{
        cout << "Handling Request: " << request << endl;
    }

    ~ComputeEngine() {
        cout << "~ComputeEngine()\n";
    }
};


struct ComputeEngineProxy : Processor{
    string env;
    static unique_ptr<Processor> processor;
    ComputeEngineProxy(const string& env): env{env} {
        cout << "ComputeEngineProxy()\n";
    };

    void handle(const string& request) override {
        if(processor == nullptr) {
            processor.reset(new ComputeEngine{env});
        }

        processor->handle(request);
    }
    
    ~ComputeEngineProxy() {
        cout << "ComputeEngineProxy()\n";
    }
};

unique_ptr<Processor> ComputeEngineProxy::processor{};

void demo_proxy() {
    cout << "--- DEMO PROXY ---\n";

    
    ComputeEngine engine{"JAVA"};
    cout << "---\n";
    engine.handle("do some multi-threading");

    cout << "--- Virtual Proxy ---\n";
    ComputeEngineProxy engineProxy{"Python with Tensorflow 2.0"};
    cout << "---\n";
    engineProxy.handle("training BERT");

}