# slider
Create a sliding window of text from an input

## About

This tool takes an input from stdin and extracts text in a sliding window fashion. Lengths of text will be created based on the user specified min and max length from the input upto a new line. Optionally, the user can specify a lower and/or upper bounded range to process the input text with.

If the input was "sometexthere" and the min-len specified was 8 and the max-len specified was 10 then the following strings would be created:\
sometexthe\
sometexth\
sometext\
ometexther\
ometexthe\
ometexth\
...\
...

This tool can be used to blindly extract phrases from various inputs, alternatively it can be used to parse data dumps in a brute-force manner without having to understand the data format as it would remove all tags and formatting associated with the input.
## Usage
`stdin | slider min max [lower] [upper]`

## Examples
Linux:
`cat inputfile.txt | slider 8 12 > output.txt`\
Windows:
`type inputfile.txt | slider 8 12 > output.txt`

The above will slide along the input and create strings of lengths 8 to 12, writing them to an output file. 

`echo somethingwashere | slider 8 12 2 15`

The above will slide along the text string "somethingwashere" starting at position 2 upto position 15 and create sub strings of lengths 8 to 12
