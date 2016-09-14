lst=["ook","ookook","oog","ooga","ug","mook","mookmook","oogam","oogum","ugug"]
def explore(word,doneRef,goal):
    if word not in goal:return 0
    elif word==goal:return 1
    elif word in doneRef:return doneRef[word]
    else:
        summ=0
        for appnd in lst:
            summ+=explore(word+appnd,doneRef,goal)
        doneRef[word]=summ
        return summ
for e in xrange(10):
    print explore("",{},raw_input())
