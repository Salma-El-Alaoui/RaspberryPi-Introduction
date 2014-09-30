int divide(int dividend, int divisor)
{
int result = 0;
int remainder = dividend;
while (remainder >= divisor) {
result++;
remainder -= divisor;
}
return result;
}
int compute_volume(int rad)
{
int rad3 = rad * rad * rad;
return divide(4*355*rad3, 3*113);
}
int kmain( void )
{
init_hw();
init_ctx(&ctx_ping, ping, STACK_SIZE);
init_ctx(&ctx_pong, pong, STACK_SIZE);
current_ctx = &ctx_init;
switch_to(&ctx_ping);
/* Pas atteignable vues nos 2 fonctions */
return(0);

}
