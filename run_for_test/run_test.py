import os

DataName = ['one', 'two', 'three']
for item in DataName:
    check = input('this is ' + item + ' test, enter y/n to run : ')
    if check != 'y':
        continue
    os.system('cp ../storage/' + item + '/code.cpp run_cpp.cpp')
    os.system('cp ../storage/' + item + '/answer.txt answer.txt')
    print('\n\n======begin building binary file to run======\n\n')
    os.system('cmake CMakeLists.txt')
    os.system('make')
    print('\n\n======begin running======')
    os.system('./test > run_ans.txt')
    print('======begin diff======')
    os.system('diff run_ans.txt answer.txt')
    print('======diff end======\n\n')

memcheckFlag = input('Do you want to do memcheck [y/n] : ')
if memcheckFlag == 'y':
    for item in DataName:
        check = input('this is ' + item + ' memcheck test, enter y/n to run : ')
        if check != 'y':
            continue
        print('\n\n======begin building binary file to run======\n\n')
        os.system('cmake CMakeLists.txt')
        os.system('make')
        print('\n\n======begin running valgrind======\n\n')
        os.system('valgrind --tool=memcheck --leak-check=full ./test')
        print('======valgrind end======\n\n')
