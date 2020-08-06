class Multa < ActiveRecord::Base
  belongs_to :pessoa
  belongs_to :emprestimo
end
