import sys, getopt, os
import pandas as pd
import elementpath
import xml.etree.ElementTree as et
from datetime import datetime


#---v10

#----------------------------------------------------------------------
def get_dt_from_html(html_file):

    #print("DEBUG!!!!! - get_dt_from_html(html_file) - Starting...")
    #print("DEBUG!!!!! - html_file=", html_file)
    
    parsed_html = et.parse(html_file)
    #print("DEBUG!!!!! - html_file parsed OK !")

    dfcols = ['tag','href', 'text', 'timeadded']
    df = pd.DataFrame(columns=dfcols)
    #print("DEBUG!!!!! - pd.DataFrame - OK !")

    a_elements = parsed_html.findall('.//a')
    #print("DEBUG!!!!! - parsed_html.findall() - OK !")
    
    for a_element in a_elements:
        #print('>>>>>a_element=', a_element)

        href = a_element.attrib.get('href')
        timeadded = a_element.attrib.get('time_added')
        tag = a_element.get('tags')
        text = a_element.findtext('.')

        df = df.append(
            pd.Series([tag, href, text, timeadded], index=dfcols),
            ignore_index=True)

    df1 = df.sort_values(['tag','timeadded'], ascending=True)
    #print("DEBUG!!!!! - get_dt_from_html(html_file) -End !")

    return  df1

#----------------------------------------------------------------------
def create_csv(df, out_file):
    df.to_csv(out_file, index = False, header=True)
    return

#----------------------------------------------------------------------
def create_html(df, out_file):
    df.to_html(out_file, index = False, header=True, render_links=True, justify='left')

    return

#----------------------------------------------------------------------
def usage():
    print('usage: Xml_2_Csv_Html.py.py -i <inputfile>')

#----------------------------------------------------------------------
def get_options(argv):
    output_file = ''

    try:
        opts, args = getopt.getopt(argv, "hi:", ["ifile="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            usage()
            sys.exit()
        elif opt in ("-i", "--ifile"):
            input_file = arg
        else:
            usage()
            sys.exit(2)
            continue

    if (input_file == ""):
        usage()
        sys.exit(2)

    return input_file

#----------------------------------------------------------------------
def fix_input_file(input_file):
    saved_file_name = input_file
    tmp_file = 'tmp-' + input_file
    with open(input_file, encoding='utf-8') as infile, open(tmp_file, 'w', encoding='utf-8') as outfile:
        for line in infile:
            #print(">>>>>line=", line)
            new_line = ''.join([char if ord(char) < 128 else '' for char in line])
            #print(">>>>>new_line=", new_line)
            outfile.write(new_line)

    os.remove(input_file)
    os.renames(tmp_file, saved_file_name)

#----------------------------------------------------------------------
def build_file_names(input_file_no_extension):
    today = datetime.today().strftime('%Y%m%d')

    input_file = input_file_no_extension + ".html"
    output_file_csv = "output-" + today + ".csv"
    output_file_html = "output-" + today + ".html"

    return input_file, output_file_csv, output_file_html

#----------------------------------------------------------------------
def main(argv):
    """ main """

    #print(sys.version)
    #print(pd.__version__)

    print('>>>>> Starting ...')
    input_file = get_options(argv)

    #print('>>>>> Building file names ...')
    input_file_html, output_file_csv, output_file_html = build_file_names(input_file)

    #print('>>>>> Fixing input file (encode issues) ...')
    #---remove invalid chars from input file
    fix_input_file(input_file_html)

    print('>>>>> Input file is:  ', input_file_html)
    print('>>>>> Output csv file:', output_file_csv)
    print('>>>>> Output html file:', output_file_html)

    #print('>>>>> Creating dataframe from input(html) file ...')
    pd.set_option('display.max_colwidth', 512)
    data_frame = get_dt_from_html(input_file_html)

    print('>>>>> Creating csv file ...')
    create_csv(data_frame, output_file_csv)

    print('>>>>> Creating html file ...')
    create_html(data_frame, output_file_html)

    #print(data_frame.to_string())
    print('>>>>> End !')
    
    return

#----------------------------------------------------------------------
if __name__ == "__main__":
    main(sys.argv[1:])

