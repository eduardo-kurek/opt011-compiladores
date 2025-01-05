; ModuleID = 'program.bc'
source_filename = "program.bc"

define i32 @func(i32 %0, float %1) {
entry:
  %c = alloca i32, align 4
  %int2float = sitofp i32 %0 to float
  %addtmp = fadd float %int2float, %1
  %convtmp = fptosi float %addtmp to i32
  store i32 %convtmp, ptr %c, align 4
  %c1 = load i32, ptr %c, align 4
  %int2float2 = sitofp i32 %c1 to float
  %multmp = fmul float %1, %int2float2
  %int2float3 = sitofp i32 %0 to float
  %subtmp = fsub float %int2float3, %multmp
  %convtmp4 = fptosi float %subtmp to i32
  ret i32 %convtmp4
  ret i32 0
}

define i32 @main() {
entry:
  %calltmp = call i32 @func(i32 100, float 9.050000e+01)
  ret i32 %calltmp
  ret i32 0
}
