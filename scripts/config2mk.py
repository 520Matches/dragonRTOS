import re

def convert_config_to_makefile(config_path, makefile_path):
    config_entries = []
    
    with open(config_path, 'r') as config_file:
        for line in config_file:
            stripped_line = line.strip()
            
            # 处理未设置的配置项（注释行）
            if stripped_line.startswith('#'):
                match = re.match(r'^#\s*(CONFIG_[A-Za-z0-9_]+)\s+is not set$', stripped_line)
                if match:
                    config_key = match.group(1)
                    config_entries.append((config_key, 'n'))
            
            # 处理已设置的配置项
            elif '=' in stripped_line:
                key, value = stripped_line.split('=', 1)
                key = key.strip()
                value = value.strip()
                
                # 去除字符串值的双引号
                if value.startswith('"') and value.endswith('"'):
                    value = value[1:-1]
                
                config_entries.append((key, value))
    
    # 写入Makefile
    with open(makefile_path, 'w') as makefile:
        for key, value in config_entries:
            makefile.write(f"{key} = {value}\n")

if __name__ == "__main__":
    convert_config_to_makefile('.config', 'config.mk')
