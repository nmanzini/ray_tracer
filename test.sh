echo "\n//////// Norming rtv1\n"
norminette ./src 
echo "\n//////// Norming libft\n"
norminette ./libft
echo "\n//////// Making\n"
make re
echo "\n//////// Testing empty\n"
./rtv1
for file in ./scenes/*
do
	echo //////// Testing ./rtv1 "$file" "\n"
	./rtv1 "$file"
done
echo "\n//////// Cleaning\n"
make fclean
