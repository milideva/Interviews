
/* C has four namespaces :
   1. labels,
   2. struct/union members (one separate namespace per struct/union)
   3. tag of a struct and union and enum (they share this namespace)
   4. ordinary identifiers : everything else : functions/variables/typedef/enum
   const
*/

struct s_tag { /* namespace 3 */
    int s_tag; /* namespace 2 */
};

int s_tag; /* everything else : namespace 4 */

void func (int s_tag) {
    int i, j;

s_tag: /* label namespace 1 */
    if (i) {
        i = s_tag; 
        goto s_tag;
    }
}

/* Note C has three linkages
   1. external (global non static variables and functions)
   2. internal (to a file scope, static)
   3. no linkage (local variables, typedef names, enum constants
*/
int main () {
    int s_tag;
    func(s_tag);
}
