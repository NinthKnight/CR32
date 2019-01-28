import QtQuick 2.9
import QtQuick.Window 2.2

Window{
    id : mainWindow;
    visible: true
    width: 640
    height: 480

    Rectangle {
        id : content;
        anchors.fill: mainWindow;

        Rectangle {
            id: head; //id
            width: mainWindow.width;
            height: mainWindow.height/4;
            color: "#FF00FF00";
            anchors.top: content.top;
            anchors.left:content.left;

        }

        Rectangle {
            id: body
            width: mainWindow.width;
            height: mainWindow.height/2;
            color: "#FF0000FF";
            anchors.top: head.bottom;
            anchors.left:content.left;
        }

        Rectangle {
            id: foot
            width: mainWindow.width;
            height: mainWindow.height/4;
            color: "#FFFF0000";
            anchors.top: body.bottom;
            anchors.left:content.left;
        }
    }
}

