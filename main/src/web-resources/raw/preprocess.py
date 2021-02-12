import os

for filename in os.listdir('.'):
    if filename.endswith(".cpp.template"): 
        print("Preprocessing file", filename)
        with open(filename, 'r') as source_file:
            with open('../' + filename.replace('.template', ''), 'w') as target_file:
                for line in source_file.read().splitlines() :
                    if line.startswith('<<<') and line.endswith('>>>'):
                        include_file_name = line[3:-3]
                        print('\tIncluding file: ', include_file_name)
                        with open(include_file_name, mode='r') as include_file:
                            target_file.write(include_file.read() + '\n')
                    else:
                        target_file.write(line + '\n')
    else:
        print("IGNORED: ", filename)
print('Done!')