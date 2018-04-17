import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: Screen.width/2
    height: Screen.height/2
    title: qsTr("Einkaufsliste")
    id:root

    ListView {
        width:root.width;
        height: root.height;


        model: MyEinkaufslisteModel{}
        delegate: Text {
            text:t
        }
        footer: EinkaufslisteFooter{}
    }
}
