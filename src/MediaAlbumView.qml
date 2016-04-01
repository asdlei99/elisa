import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQml.Models 2.1
import org.mgallien.QmlExtension 1.0
import QtMultimedia 5.4
import QtQuick.Layouts 1.2

Item {
    id: topListing
    property var rootIndex
    property StackView stackView
    property var contentModel
    property MediaPlayList playListModel
    property var albumName
    property var artistName
    property var tracksCount
    property var albumArtUrl

    width: stackView.width
    height: stackView.height

    Component {
        id: rowDelegate

        Item {
            id: rowDelegateContent
            height: Screen.pixelDensity * 15.
            Rectangle {
                color: "#FFFFFF"
                anchors.fill: parent
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Button {
            id: backButton

            height: Screen.pixelDensity * 8.
            Layout.preferredHeight: height
            Layout.minimumHeight: height
            Layout.maximumHeight: height
            Layout.fillWidth: true

            onClicked: if (listingView.depth > 1) {
                           listingView.pop()
                       } else {
                           parentStackView.pop()
                       }
            text: 'Back'
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            spacing: 0

            ColumnLayout {
                Layout.preferredWidth: topListing.width / 2
                Layout.fillHeight: true

                spacing: 0

                TableView {
                    id: contentDirectoryView

                    model: DelegateModel {
                        model: contentModel
                        rootIndex: topListing.rootIndex

                        delegate: AudioTrackDelegate {
                            height: Screen.pixelDensity * 15.
                            width: contentDirectoryView.width

                            hoverAction: Action {
                                id: queueTrack

                                iconSource: 'image://icon/media-playback-start'

                                onTriggered: topListing.playListModel.enqueue(contentDirectoryView.model.modelIndex(index))
                            }

                            title: if (model != undefined && model.title !== undefined)
                                       model.title
                                   else
                                       ''
                            artist: if (model != undefined && model.artist !== undefined)
                                        model.artist
                                    else
                                        ''
                            itemDecoration: if (model != undefined && model.image !== undefined)
                                                model.image
                                            else
                                                ''
                            duration: if (model != undefined && model.duration !== undefined)
                                          model.duration
                                      else
                                          ''
                            trackRating: if (model != undefined && model.rating !== undefined)
                                             model.rating
                                         else
                                             ''
                            isPlaying: if (model != undefined && model.isPlaying !== undefined)
                                           model.isPlaying
                                       else
                                           false
                        }
                    }

                    backgroundVisible: false
                    headerVisible: false
                    frameVisible: false
                    focus: true
                    rowDelegate: rowDelegate

                    TableViewColumn {
                        role: "title"
                        title: "Title"
                    }

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

            Rectangle {
                border.width: 1
                border.color: "#DDDDDD"
                color: "#DDDDDD"

                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                Layout.preferredHeight: parent.height - Screen.pixelDensity * 5.
                Layout.preferredWidth: 1
                Layout.minimumWidth: 1
                Layout.maximumWidth: 1
            }

            ContextView {
                id: albumContext

                Layout.preferredWidth: topListing.width / 2
                Layout.fillHeight: true

                albumArtUrl: topListing.albumArtUrl
                albumName: topListing.albumName
                tracksCount: topListing.tracksCount
                artistName: topListing.artistName
            }
        }
    }
}