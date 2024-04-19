#include <system/drivers/driver.hpp>

class Driver
    {
    private:
        char* Name;
        char* Description;
    public:
        Driver(char* name = 0, char* description = 0);

        char* GetDriverName();
        char* GetDriverDescription();

        virtual bool Initialize();
    };

extern 