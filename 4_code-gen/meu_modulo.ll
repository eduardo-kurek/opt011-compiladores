; ModuleID = 'meu_modulo.bc'
source_filename = "meu_modulo.bc"

define i32 @soma(i32 %0, i32 %1) {
entry:
  %sum = add i32 %0, %1
  ret i32 %sum
}

define i32 @main() {
entry:
  %call_soma = call i32 @soma(i32 1, i32 5)
  ret i32 %call_soma
}
