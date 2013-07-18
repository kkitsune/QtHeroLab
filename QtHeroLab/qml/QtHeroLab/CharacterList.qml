import QtQuick 2.0

Image
{
	id: bg
	signal charSelected(string name)
	signal back

	fillMode: Image.Tile
	source: "background.bmp"

	anchors.rightMargin: 25
	anchors.leftMargin: 25
	anchors.bottomMargin: 25
	anchors.topMargin: 25
	anchors.fill: parent

	Component.onCompleted: view.parent = bg

	property ListView view: ListView
	{
		anchors.topMargin: backBtn.height
		anchors.fill: parent
		clip: true
		model: ListModel { }
		delegate: Item
		{
			height: row.height + 5
			Row
			{
				id: row
				spacing: 5
				CustomListElement
				{
					text: name
					anchors.verticalCenter: parent.verticalCenter
					onClicked: bg.charSelected(view.model.get(index).name)
				}
			}
		}
	}

	MouseArea
	{
		anchors.top: parent.top
		anchors.left: parent.left
		height: backBtn.height
		width: 100

		hoverEnabled: true
		onEntered: backBtn.color = "darkgray"
		onExited: backBtn.color = "black"

		onClicked: parent.back()

		Text
		{
			id: backBtn
			Component.onCompleted: if(platform.isAndroid) font.pixelSize *= 2
			text: "<- Back"
			font.pixelSize: 15
			color: "black"
			font.bold: true
		}
	}
}
