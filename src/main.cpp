#include <application.h>
#include <memory>

int main(int argc, char *argv[])
{
  std::unique_ptr<Application> application = std::make_unique<Application>();

  application->Run();

	return 0;
}
