import QtQuick 1.0

 Rectangle {
     color: "white"
     width: 200
     height: 100
     property variant model

     /*
     Text {
         text: "?"
         anchors.horizontalCenter: parent.horizontalCenter
         font.pointSize: 10
         function findGreetings() {
             var db = openDatabaseSync("hallo", "1.0", "The Example QML SQL!", 1000000);

             db.transaction(
                 function(tx) {
                     // Create the database if it doesn't already exist
                     tx.executeSql('CREATE TABLE IF NOT EXISTS word(ID INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, mean TEXT, date NUMERIC, other ENUM)');

                     // Add (another) row
                     var cmd = 'INSERT INTO word (name, mean, date, other) VALUES (';
                     for(var i = 0; i < 10; i++)
                         tx.executeSql('INSERT INTO word (name, mean, date, other) VALUES (\'hello\', \'world\', 20120822, \'X\')');

                     // Show all added greetings
                     var rs = tx.executeSql('SELECT * FROM word');
                     model = rs;

                     var r = ""
                     for(var i = 0; i < rs.rows.length; i++) {
                         r += rs.rows.item(i).ID + ", "
                         r += rs.rows.item(i).name + ", " 
                         r += rs.rows.item(i).mean + ", " 
                         r += rs.rows.item(i).date +", "
                         r += rs.rows.item(i).other +", "
                         r += "\n"
                     }
                     text = r
                 }
             )
         }

         Component.onCompleted: findGreetings()
     }
     */
         function findGreetings() {
             var db = openDatabaseSync("hallo", "1.0", "The Example QML SQL!", 1000000);

             db.transaction(
                 function(tx) {
                     // Create the database if it doesn't already exist
                     tx.executeSql('CREATE TABLE IF NOT EXISTS word(ID INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, mean TEXT, date NUMERIC, other ENUM)');

                     // Add (another) row
                     var cmd = 'INSERT INTO word (name, mean, date, other) VALUES (';
                     for(var i = 0; i < 10; i++)
                         tx.executeSql('INSERT INTO word (name, mean, date, other) VALUES (\'hello\', \'world\', 20120822, \'X\')');

                     // Show all added greetings
                     var rs = tx.executeSql('SELECT * FROM word');
                     model = rs.rows

                     var r = ""
                     for(var i = 0; i < rs.rows.length; i++) {
                         r += rs.rows.item(i).ID + ", "
                         r += rs.rows.item(i).name + ", "
                         r += rs.rows.item(i).mean + ", "
                         r += rs.rows.item(i).date +", "
                         r += rs.rows.item(i).other +", "
                         r += "\n"
                     }
                     print(r)
                 }
             )
         }

        Component {
            id: wordDelegate
            Rectangle {
                id: wordCard
                height: 80
                width: parent.width

                Text {
                    id: wordLabelartistsSqlModel
                    width: parent.width
                    text: wordName
                    font.bold: true; font.pointSize: 16
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    id: detailLabel
                    width: parent.width
                    text: wordDetail
                    font.bold: true; font.pointSize: 16
                    horizontalAlignment: Text.AlignLeft
                    visible: false
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        var info = {"wordName":wordName, "wordDetail":wordDetail}
                        if(Global.newPage == null)
                            Global.newPage = Qt.createComponent("newpage.qml")
                        pageStack.push(Global.newPage, {message: info})
                    }
                }
            }
        }

        ListView {
            id: listView
            width: parent.width
            anchors.fill: parent

            spacing: 2
            model: model
            delegate: wordDelegate
            preferredHighlightBegin: 0; preferredHighlightEnd: 0
            highlightRangeMode: ListView.StrictlyEnforceRange
            orientation: ListView.Vertical
            snapMode: ListView.SnapToItem;
            flickDeceleration: 2000

        }
         Component.onCompleted: findGreetings()
 }
