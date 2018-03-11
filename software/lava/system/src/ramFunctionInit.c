
/**
 * @brief This function is called by the startup code to copy
 *        RAM based functions out of flash and into RAM.
 */
void ramFunctionInit(void)
{
    // These variables are defined in the linker script
    extern char _ram_function_lma;
    extern char _s_ram_function_vma;
    extern char _e_ram_function_vma;

    char *src = &_ram_function_lma;
    char *dst = &_s_ram_function_vma;

    while(dst < &(_e_ram_function_vma))
    {
        *dst++ = *src++;
    }
}

