import os
import re
import sys
import textwrap

from kconfiglib import Kconfig, split_expr, expr_value, expr_str, BOOL, \
                       TRISTATE, TRI_TO_STR, AND, OR

def generate_config(kconfig_file,config_in, config_out, header_out):

    print("Parsing " + kconfig_file)
    kconf = Kconfig(kconfig_file, warn_to_stderr=False, 
                    suppress_traceback=True)

    # Load config files
    print(kconf.load_config(config_in))

    # Write merged config        
    print(kconf.write_config(config_out))

    # Write headers
    print(kconf.write_autoconf(header_out))

    with open(header_out, 'r+') as header_file:

        content = header_file.read()
        header_file.truncate(0)
        header_file.seek(0)

        # Remove CONFIG_ and MR_USING_XXX following number
        content = content.replace("#define CONFIG_", "#define ")

        # Add the micro
        header_file.write("#ifndef __CONFIG_H\n") 
        header_file.write("#define __CONFIG_H\n\n")

        header_file.write("#ifdef __cplusplus\n")
        header_file.write("extern \"C\" {\n") 
        header_file.write("#endif /* __cplusplus */\n\n")

        # Write back the original data
        header_file.write(content)

        # Add the micro
        header_file.write("\n#ifdef __cplusplus\n")
        header_file.write("}\n")
        header_file.write("#endif /* __cplusplus */\n\n")
        header_file.write("#endif /* __CONFIG_H*/\n")

def main():
    kconfig_file = 'Kconfig' 
    config_in = '.config'
    config_out = '.config'
    header_out = 'dragon_config.h'
    generate_config(kconfig_file, config_in, config_out, header_out)

if __name__ == "__main__":
    main()
