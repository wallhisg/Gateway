#include <Homepage/Homepage.h>

WebApplication::WebApplication(const WEnvironment &env)
    : WApplication(env)
{
    setTitle("Web Application");
    setTheme(new WBootstrapTheme(this));
}
