#ifndef HOMEPAGE_H_
#define HOMEPAGE_H_

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>

#include <iostream>

using namespace Wt;
using namespace std;

class WebApplication : public WApplication
{
public:
    WebApplication(const WEnvironment &env);
};

#endif
