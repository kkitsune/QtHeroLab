import QtQuick 2.0
import HeroLab 1.0

Image
{
	width: 800
	height: 600
	fillMode: Image.Tile
	source: "mainwindow.bmp"

	Portfolio
	{
		property QtObject path : FileLister { }
		property var dir

		Component.onCompleted:
		{
			dir = path.list();
			fillList();
		}

		function fillList()
		{
			if(path.level > 0)
				porList.model.append({"name": "../"});
			for(var i = 0; i < dir.length; i++)
				porList.model.append({"name": dir[i]});
		}

		function onFileSelected(index)
		{
			var t = porList.model.get(index).name;
			if(t[t.length - 1] === "/")
			{
				if(t === "../")
				{
					path.upOne();
					dir = path.list();
				}
				else
					dir = path.list(t);
				porList.model.clear();
				fillList();
			}
			else
			{
				file = t;
				porList.model.clear();
			}
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
