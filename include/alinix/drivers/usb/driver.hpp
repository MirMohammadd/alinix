#ifndef __ALINIX_KERNEL_INCLUDED_DRIVER_HPP
#define __ALINIX_KERNEL_INCLUDED_DRIVER_HPP


namespace alinix{
    namespace drivers{
        namespace usb{
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
        }
    }
}


#endif // __ALINIX_KERNEL_INCLUDED_DRIVER_HPP