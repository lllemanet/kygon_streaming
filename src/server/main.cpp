#include "Application.hpp"
#include "common/Utils.hpp"

int main(int argc, char* argv[]) {
    kygon::server::Application app{argc, argv};
    if (!app.init()) {
        return -1;
    }

    return app.exec();
}
