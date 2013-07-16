import QtQuick 2.0
import HeroLab 1.0

Image
{
	width: 800
	height: 600
	fillMode: Image.Tile
	source: "mainwindow.bmp"

	FileLister { id: path }
	Portfolio
	{
		Component.onCompleted:
		{
			var list = path.list();
			for(var i = 0; i < list.length; i++)
				porList.model.append({"name" : list[i]});
		}

		function onFileSelected(index)
		{
			porList.model.clear()
		}

		id: por
	}

	ListView
	{
		id: porList
		clip: true
		anchors.rightMargin: 25
		anchors.leftMargin: 25
		anchors.bottomMargin: 25
		anchors.topMargin: 25
		anchors.fill: parent
		model: ListModel { }
		delegate: Item
		{
			height: row.height + 5
			Row
			{
				id: row
				spacing: 5
				FileElement
				{
					text: name
					anchors.verticalCenter: parent.verticalCenter
					onClicked: por.onFileSelected(index)
				}
			}
		}
	}
}
