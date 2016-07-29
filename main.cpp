#include <gtk/gtk.h>
#include <iostream>
#include <map>
#include <string>
#include <regex>

extern "C" {

    class Gtk {
        public:
            Gtk& init( int * argc, char **argv[] ) {
                gtk_init(argc, argv);   
                _window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                g_signal_connect( _window, "destroy", G_CALLBACK(gtk_main_quit), NULL );
                
                _grid = gtk_grid_new ();

                return *this;
            }

            Gtk() {

            }

            Gtk& operator()( std::string selector ){
                this->_selector = selector;
                return *this;
            }

            Gtk& set_size( int width, int height ) {
                gtk_window_set_default_size (GTK_WINDOW (_window), width, height);
                return *this;
            }

            Gtk& set_title( std::string title ) {
                gtk_window_set_title(GTK_WINDOW(_window), title.c_str() );
                return *this;
            }

            std::string button( std::string str, std::map <std::string, std::string> attr ) {

                std::string id = "#"+attr["id"];

                this->_object = gtk_button_new_with_label ( str.c_str() );

                this->_ids[ id ] = _object;

                return id;
            }

            void onclick( void(*callback)() ) {
                g_signal_connect (this->_ids[ this->_selector ], "clicked",  G_CALLBACK( callback ), NULL);
            }


            void label( std::string str ) {
                GtkWidget *label = gtk_label_new( str.c_str() );
                gtk_container_add(GTK_CONTAINER(_window), label);
            }

            void html( std::string str ) {

            }

            void br() {
                _i = 0;
                _grid = gtk_grid_new ();
            }

            ~Gtk() {
                gtk_container_add(GTK_CONTAINER(_window), _grid);

               // std::cout << _br << std::endl;

                for( auto const &x : _ids ) {
                    gtk_grid_attach (GTK_GRID (_grid),  x.second, _i, 0, 1, 1);
                    ++_i;
                }

                gtk_widget_show_all(_window);
                gtk_main();
            }

        
        private:
            GtkWidget * _window;
            GtkWidget * _object;
            GtkWidget * _grid;
            std::map<std::string, GtkWidget*> _ids;
            std::string _selector;

            int _i = 1;

    };
}


int main (int argc, char *argv[])
{
    Gtk window;
    window.init( &argc, &argv ).set_title( "test ast" ).set_size( 200, 200 );

    //window.html("<button id='button_id' class='test'>Test ast</button>");

    window.button("Test ast",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id" },
    } );


    window.button("Test ast11111",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id1" },
    } );

    window.br();

    window.button("Test ffdasd",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id2" },
    } );



    window("#button_id").onclick([]() {
        std::cout << "test" << std::endl;
    });

    return 0;
}
