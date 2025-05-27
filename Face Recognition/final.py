import cv2
import numpy as np
import os
import face_recognition
from datetime import datetime

cap = cv2.VideoCapture(0)

path = 'data'
stdImg = []
stdName = []
myList = os.listdir(path)

for cl in myList:
    curimg = cv2.imread(f'{path}/{cl}')
    stdImg.append(curimg)
    stdName.append(os.path.splitext(cl)[0])

studentName = [name.upper() for name in stdName]

print('Student Names in the List is :',studentName)

s1 = 0
s2 = 0
s3 = 0
s4 = 0
s5 = 0

stdname_copy = studentName.copy()


def resize(img, size) :
    width = int(img.shape[1]*size)
    height = int(img.shape[0] * size)
    dimension = (width, height)
    return cv2.resize(img, dimension, interpolation= cv2.INTER_AREA)

def findEncoding(images) :
    imgEncodings = []
    for img in images :
        img = resize(img, 0.50)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        encodeimg = face_recognition.face_encodings(img)[0]
        imgEncodings.append(encodeimg)
    return imgEncodings

EncodeList = findEncoding(stdImg)


while True :
    success, frame = cap.read()
    Smaller_frames = cv2.resize(frame, (0,0), None, 0.25, 0.25)

    facesInFrame = face_recognition.face_locations(Smaller_frames)
    encodeFacesInFrame = face_recognition.face_encodings(Smaller_frames, facesInFrame)

    for encodeFace, faceloc in zip(encodeFacesInFrame, facesInFrame) :
        matches = face_recognition.compare_faces(EncodeList, encodeFace)
        facedis = face_recognition.face_distance(EncodeList, encodeFace)
        matchIndex = np.argmin(facedis)

        if matches[matchIndex] :
            name = studentName[matchIndex].upper()
            y1, x2, y2, x1 = faceloc
            y1, x2, y2, x1 = y1*4, x2*4, y2*4, x1*4
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 3)
            cv2.rectangle(frame, (x1, y2-25), (x2, y2), (0, 255, 0), cv2.FILLED)
            cv2.putText(frame, name, (x1+6, y2-6), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 2)

            if name == 'NEHA':            
                s1 += 1
                if s1 >= 10:
                    print('NEHA is detected')

                    s1 = 0
                    s2 = 0
                    s3 = 0
                    s4 = 0
                    s5 = 0
                    
            if name == 'KAVYA':            
                s2 += 1
                if s2 >= 10:
                    print('KAVYA is detected')

                    s1 = 0
                    s2 = 0
                    s3 = 0
                    s4 = 0
                    s5 = 0
             
        else:
            intruder_images=[]
            intruder_count=0
            y1, x2, y2, x1 = faceloc
            y1, x2, y2, x1 = y1*4, x2*4, y2*4, x1*4
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 3)
            cv2.putText(frame, 'INTRUDER', (x1+6, y2-6), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 2)
          
    cv2.imshow('Face Attendance System',frame)
    k = cv2.waitKey(1)
    if k == 27:
        break
    
cap.release()
cv2.destroyAllWindows()