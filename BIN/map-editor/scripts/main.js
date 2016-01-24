
window.CONFIG = {};
CONFIG['maxid'] = 7;
CONFIG['sprites'] = 'sprites/';

function parse(rawdata)
{
	if(typeof(rawdata)!='string' || rawdata=='')
	{
		var map = [];
		for(var row=0;row<10;++row)
		{
			map[row]=[];
			for(var col=0;col<14;++col)
				map[row][col]=0;
		}
		return map;
	}
	var map = rawdata.split('\n');
	for (var i = 0; i < map.length; ++i)
		map[i] = map[i].split(' ');
	return map;
}

function fill(map)
{
	var str = "";
	for (var row = 0; row < 10; ++row){
		for (var col = 0; col < 14; ++col){
			str += map[row][col] + " ";
		}
		str += "\n";
	}
	$(".edytowanie").val(str).trigger("input");
}

function eventOnElement(obj)
{
	var col = obj.data('col');
	var row = obj.data('row');
	var map = parse($(".edytowanie").val());
	if(map[row][col]<CONFIG['maxid'])
		++map[row][col];
	else
		map[row][col]=1;
	fill(map);
	$(".edytowanie").trigger("input");
	
}

$(document).ready(function(){
	$(".edytowanie").hide();
	$(".edytowanie").bind("input", function(){
		// parsowanie
		var map = parse($(".edytowanie").val());
		// nowa tabela
		var table = "<table><tbody>";
		for (var row = 0; row < 10; ++row){
			table += "<tr>";
			for (var col = 0; col < 14; ++col){
				table += '<td data-col="' + col + '" data-row="' + row + '" style="background: url('+ CONFIG['sprites'] + map[row][col] + '.png)"></td>';
			}
			table += "</tr>";
		}
		table += "</tbody></table>";
		// podmiana
		var hand = $('.podglad');
		hand.children().remove();
		hand.append(table);
		hand.find('td').on("click", function(){
			eventOnElement($(this));
		});
	}).trigger("input");

	$("#fill").on("click", function(){
		var str = "";
		for (var row = 0; row < 10; ++row){
			for (var col = 0; col < 14; ++col){
				str += $(".fill_param").val() + " ";
			}
			str += "\n";
		}
		$(".edytowanie").val(str).trigger("input");
	});

	$("#show_hide").on("click", function(){
		if($(".edytowanie").data('view')=='show')
		{
			$(".edytowanie").hide();
			$(".edytowanie").data('view', 'hide');
		}
		else
		{
			$(".edytowanie").show();
			$(".edytowanie").data('view', 'show');
		}
	});

	$("#save").on("click", function(){
		if($(".edytowanie").val()=='')
		{
			alert('Proszę wypełnić mapę!');
			return false;
		}
		var filename = $(".filename").val().replace(/.map$/,'');
		if(filename=='')
			filename='mapafis.map';
		else filename+='.map';
		var blob = new Blob([$(".edytowanie").val()], {
			type: "text/plain;charset=utf-8;",
		});
		saveAs(blob, filename);
	});
});
