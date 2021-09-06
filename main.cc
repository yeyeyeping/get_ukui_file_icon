#include<gtk/gtk.h>
#include<gio/gio.h>
#include<string>
#include <napi.h>

using namespace Napi;
using std::string;
/*
native method  get_icon
desc:get icon thrrough gtk,gio
param : filename ,icon size
dependency:gtk 3.0
if you only want to get .so library,extract this function and delete eveything relative to napi,
then use "gcc main.c -fPIC -shared -o libiconget.so `pkg-config --cflags --libs gtk+-3.0`" command to compile it.

*/
string get_icon(const string& filename,const int size){
    string result= "unknown";
    //get file from path
    GFile* file = g_file_new_for_path(filename.c_str());
    GError* gerror = 0;
    //query "standard::icon" info from file
    GFileInfo* gfileinfo = g_file_query_info(file,"standard::icon", GFileQueryInfoFlags::G_FILE_QUERY_INFO_NONE,g_cancellable_new(), &gerror);
    if (gerror) {
        g_error_free(gerror);
        gerror = 0;
    }
    if (gfileinfo) {
        //get icon name from gfileinfo
        GIcon* icon = g_file_info_get_icon (gfileinfo);
        if(icon){
            GtkIconTheme* theme = gtk_icon_theme_new();
            //add some ukui paths
            gtk_icon_theme_append_search_path(theme,"/usr/share/icons/ukui/48x48/places");
            gtk_icon_theme_append_search_path(theme,"/usr/share/icons/ukui/48x48/mimetypes");
            gtk_icon_theme_append_search_path(theme,"/usr/share/icons/ukui/48x48/apps");
            gtk_icon_theme_append_search_path(theme,"/usr/share/icons/ukui/48x48/devices");
            GtkIconInfo* info = 0;
            //lookup icon
            info = gtk_icon_theme_lookup_by_gicon (theme,icon,size,GtkIconLookupFlags::GTK_ICON_LOOKUP_NO_SVG);
           if(info){
               //copy result
               result = gtk_icon_info_get_filename(info);
               //free info
               g_object_unref(info);
           }
            g_object_unref(theme);
        }
        //free gfileinfo,file,theme

        g_object_unref(gfileinfo);
        g_object_unref(file);

    }
    return result;
}
//transfer  params  from node and call c++ native method get_icon
String call_get_icon(const CallbackInfo& info){
    Env env = info.Env();
    string filename = info[0].As<String>().Utf8Value();
    int size = info[1].ToNumber().Int32Value();
    return String::New(env,get_icon(filename,size));
}
//export method
Napi::Object Init(Env env, Object exports) {
  exports.Set("get_icon", Function::New(env, call_get_icon));
  return exports;
}
NODE_API_MODULE(addon, Init)