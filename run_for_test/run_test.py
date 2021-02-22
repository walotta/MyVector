import os

DataName = ['one', 'two', 'three']
for item in DataName:
    check = input('this is ' + item + ' test, enter y/n to run :')
    if check != 'y':
        exit(0)
    os.system('cp ../storage/' + item + '/code.cpp run_cpp.cpp')
    os.system('cp ../storage/' + item + '/answer.txt answer.txt')
    os.system('cmake CMakeLists.txt')
    os.system('make')
    os.system('./test > run_ans.txt')
    os.system('diff run_ans.txt answer.txt')
