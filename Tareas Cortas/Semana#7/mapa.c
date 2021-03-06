/* 
LUIS EDUARDO ROJAS CARRILLO - B86875.
MAPA.H.
DESARROLLO DE MÉTODOS.
ESTRUCTURA DE DATOS PARA GUARDAR LA CANTIDAD DE ETIQUETAS.
*/
#include "mapa.h"

mapa::mapa(){//INICIALIZA EL MAPA CON TODAS LAS ETIQUETAS.
	cant=0;

	map["!–…–"]=0; 	
	map["!DOCTYPE"]=0; 	
	map["a"]=0; 	
	map["abbr"]=0;
	map["address"]=0; 
	map["area"]=0;
	map["article"]=0;
	map["aside"]=0;
	map["audio"]=0;
	map["b"]=0;
	map["base"]=0;
	map["bdi"]=0; 
	map["bdo"]=0;
	map["blockquote"]=0;
	map["body"]=0;
	map["br"]=0;
	map["button"]=0;
	map["canvas"]=0;
	map["caption"]=0;
	map["cite"]=0;	
	map["code"]=0;	
	map["col"]=0;	
	map["colgroup"]=0;	
	map["command"]=0;	
	map["datalist"]=0;	
	map["dd"]=0;	
	map["del"]=0;	
	map["details"]=0;	
	map["dfn"]=0;	
	map["dialog"]=0;	
	map["div"]=0;	
	map["dl"]=0;	
	map["dt"]=0;	
	map["em"]=0;	
	map["embed"]=0;
	map["fieldset"]=0;	
	map["figcaption"]=0;	
	map["figure"]=0;	
	map["footer"]=0;	
	map["form>"]=0;	
	map["h1"]=0;	
	map["h6"]=0;	
	map["head"]=0;	
	map["header"]=0;	
	map["hgroup"]=0;	
	map["hr"]=0;	
	map["html"]=0;	
	map["i"]=0;	
	map["iframe"]=0;	
	map["img"]=0;	
	map["input"]=0;	
	map["ins"]=0;	
	map["kbd"]=0;	
	map["keygen"]=0;	
	map["label"]=0;	
	map["legend"]=0;	
	map["li"]=0;	
	map["link"]=0;	
	map["map"]=0;	
	map["mark"]=0;	
	map["menu"]=0;	
	map["meta"]=0;	
	map["meter"]=0;	
	map["nav"]=0;	
	map["noscript"]=0;	
	map["objet"]=0;	
	map["ol"]=0;	
	map["optgroup"]=0;	
	map["option"]=0;	
	map["output"]=0;	
	map["p"]=0;	
	map["param"]=0;	
	map["pre"]=0;	
	map["progress"]=0;	
	map["q"]=0;	
	map["rp"]=0;	
	map["rt"]=0;	
	map["ruby"]=0;	
	map["s"]=0;	
	map["samp"]=0;	
	map["script"]=0;	
	map["section"]=0;	
	map["select"]=0;	
	map["small"]=0;	
	map["source"]=0;	
	map["span"]=0;	
	map["strong"]=0;	
	map["style"]=0;	
	map["sub"]=0;	
	map["summary"]=0;	
	map["sup"]=0;	
	map["table"]=0;	
	map["tbody"]=0;	
	map["td"]=0;	
	map["textarea"]=0;	
	map["tfoot"]=0;	
	map["th"]=0;	
	map["thead"]=0;	
	map["time"]=0;	
	map["title"]=0;	
	map["tr"]=0;	
	map["track"]=0;	
	map["ul"]=0;	
	map["var"]=0;	
	map["video"]=0;
	map["wbr"]=0;
	map["/!–…–"]=0; 	
	map["/!DOCTYPE"]=0; 	
	map["/a"]=0; 	
	map["/abbr"]=0;
	map["/address"]=0; 
	map["/area"]=0;
	map["/article"]=0;
	map["/aside"]=0;
	map["/audio"]=0;
	map["/b"]=0;
	map["/base"]=0;
	map["/bdi"]=0; 
	map["/bdo"]=0;
	map["/blockquote"]=0;
	map["/body"]=0;
	map["/br"]=0;
	map["/button"]=0;
	map["/canvas"]=0;
	map["/caption"]=0;
	map["/cite"]=0;	
	map["/code"]=0;	
	map["/col"]=0;	
	map["/colgroup"]=0;	
	map["/command"]=0;	
	map["/datalist"]=0;	
	map["/dd"]=0;	
	map["/del"]=0;	
	map["/details"]=0;	
	map["/dfn"]=0;	
	map["/dialog"]=0;	
	map["/div"]=0;	
	map["/dl"]=0;	
	map["/dt"]=0;	
	map["/em"]=0;	
	map["/embed"]=0;
	map["/fieldset"]=0;	
	map["/figcaption"]=0;	
	map["/figure"]=0;	
	map["/footer"]=0;	
	map["/form>"]=0;	
	map["/h1"]=0;	
	map["/h6"]=0;	
	map["/head"]=0;	
	map["/header"]=0;	
	map["/hgroup"]=0;	
	map["/hr"]=0;	
	map["/html"]=0;	
	map["/i"]=0;	
	map["/iframe"]=0;	
	map["/img"]=0;	
	map["/input"]=0;	
	map["/ins"]=0;	
	map["/kbd"]=0;	
	map["/keygen"]=0;	
	map["/label"]=0;	
	map["/legend"]=0;	
	map["/li"]=0;	
	map["/link"]=0;	
	map["/map"]=0;	
	map["/mark"]=0;	
	map["/menu"]=0;	
	map["/meta"]=0;	
	map["/meter"]=0;	
	map["/nav"]=0;	
	map["/noscript"]=0;	
	map["/objet"]=0;	
	map["/ol"]=0;	
	map["/optgroup"]=0;	
	map["/option"]=0;	
	map["/output"]=0;	
	map["/p"]=0;	
	map["/param"]=0;	
	map["/pre"]=0;	
	map["/progress"]=0;	
	map["/q"]=0;	
	map["/rp"]=0;	
	map["/rt"]=0;	
	map["/ruby"]=0;	
	map["/s"]=0;	
	map["/samp"]=0;	
	map["/script"]=0;	
	map["/section"]=0;	
	map["/select"]=0;	
	map["/small"]=0;	
	map["/source"]=0;	
	map["/span"]=0;	
	map["/strong"]=0;	
	map["/style"]=0;	
	map["/sub"]=0;	
	map["/summary"]=0;	
	map["/sup"]=0;	
	map["/table"]=0;	
	map["/tbody"]=0;	
	map["/td"]=0;	
	map["/textarea"]=0;	
	map["/tfoot"]=0;	
	map["/th"]=0;	
	map["/thead"]=0;	
	map["/time"]=0;	
	map["/title"]=0;	
	map["/tr"]=0;	
	map["/track"]=0;	
	map["/ul"]=0;	
	map["/var"]=0;	
	map["/video"]=0;
	map["/wbr"]=0;	
}
		
mapa::~mapa(){//LIMPIA EL MAPA.
	map.clear();
}

void mapa::insertar(string dato){//AUMENTA EL CONTADOR DE ETIQUETAS SI EXISTE LA LLAVE.
	it=map.find(dato);
	if(it!=map.end()){
	it->second++;	
	cant++;
	}
}

void mapa::muestre(){//MUESTRA TODAS LAS ETIQUETAS MIENTRAS EL VALOR SEA DISTINTO DE 0.
	cout<<"*Etiquetas: "<<endl;
	for(it=map.begin(); it!=map.end(); it++){
		if(it->second!=0){
		cout<<"Etiqueta:" <<"<"<<it->first<<">"<<"  "<<"Cantidad: "<<it->second<<endl;
		}
	}
	cout<<"*Total etiquetas: "<<cant<<endl;
}
